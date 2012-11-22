#include "Mesh.hpp"

e3e::Mesh::Mesh() :
	ready(false)
{
	glGenBuffers(3, geometryBuffers);
	glGenBuffers(2, facenormalsBuffers);
	glGenBuffers(2, vertexnormalsBuffers);
	glGenVertexArrays(3, vaos);
	glGenBuffers(2, indexBuffers);

	normal_state.draw_face_normals = false;
	normal_state.draw_vertex_normals = false;
	normal_state.face_normals_ok = false;
	normal_state.vertex_normals_ok = false;

}

void e3e::Mesh::subdivideQuads()
{
	std::vector<e3e::Face> outputFaces;
	std::vector<e3e::Vector3d> outputNormals;
	std::vector<e3e::Vector3d> outputVertices;
	std::vector<e3e::Vector2d> outputUv;

	for(unsigned int fi=0; fi < faces.size(); fi++)
	{
		e3e::Face f = faces[fi];
		// only quads !
		if(f.nbIndices() == 4)
		{

			e3e::Vector3d v1, v2, v3, v4;

			v1 = vertices[f.indices[0]];
			v2 = vertices[f.indices[1]];
			v3 = vertices[f.indices[2]];
			v4 = vertices[f.indices[3]];

			e3e::Vector3d v12, v23, v34, v14, v13;
			v12 = (v1+v2)/2.f;
			v23 = (v2+v3)/2.f;
			v34 = (v3+v4)/2.f;
			v14 = (v1+v4)/2.f;
			v13 = (v1+v3)/2.f;


			e3e::Vector2d uv1, uv2, uv3, uv4;
			uv1 = uvCoords[f.indices[0]];
			uv2 = uvCoords[f.indices[1]];
			uv3 = uvCoords[f.indices[2]];
			uv4 = uvCoords[f.indices[3]];

			e3e::Vector2d uv12, uv23, uv34, uv14, uv13;
			uv12 = (uv1+uv2)/2.f;
			uv23 = (uv2+uv3)/2.f;
			uv34 = (uv3+uv4)/2.f;
			uv14 = (uv1+uv4)/2.f;
			uv13 = (uv1+uv3)/2.f;

			// 0 1 2
			// 3 4 5
			// 6 7 8
			outputVertices.push_back(v1); outputVertices.push_back(v12); outputVertices.push_back(v2);
			outputVertices.push_back(v14); outputVertices.push_back(v13); outputVertices.push_back(v23);
			outputVertices.push_back(v4); outputVertices.push_back(v34); outputVertices.push_back(v3);

			outputUv.push_back(uv1); outputUv.push_back(uv12); outputUv.push_back(uv2);
			outputUv.push_back(uv14); outputUv.push_back(uv13); outputUv.push_back(uv23);
			outputUv.push_back(uv4); outputUv.push_back(uv34); outputUv.push_back(uv3);


			// normals
			if(normal_state.vertex_normals_ok)
			{
				e3e::Vector3d n1, n2, n3, n4;
				e3e::Vector3d n12, n23, n34, n14, n13;

				n1 = vertexNormals[f.indices[0]];
				n2 = vertexNormals[f.indices[1]];
				n3 = vertexNormals[f.indices[2]];
				n4 = vertexNormals[f.indices[3]];

				n12 = n1+n2; n12.normalize();
				n23 = n2+n3; n23.normalize();
				n34 = n3+n4; n34.normalize();
				n14 = n1+n4; n14.normalize();
				n13 = n1+n3; n13.normalize();

				outputNormals.push_back(n1); outputNormals.push_back(n12); outputNormals.push_back(n2);
				outputNormals.push_back(n14); outputNormals.push_back(n13); outputNormals.push_back(n23);
				outputNormals.push_back(n4); outputNormals.push_back(n34); outputNormals.push_back(n3);
			}



			unsigned int offset = fi*9;
			e3e::Face f1, f2, f3, f4;

			f1.indices.push_back(offset + 0); f1.indices.push_back(offset + 1);
			f1.indices.push_back(offset + 4); f1.indices.push_back(offset + 3);

			f2.indices.push_back(offset + 1); f2.indices.push_back(offset + 2);
			f2.indices.push_back(offset + 5); f2.indices.push_back(offset + 4);

			f3.indices.push_back(offset + 4); f3.indices.push_back(offset + 5);
			f3.indices.push_back(offset + 8); f3.indices.push_back(offset + 7);

			f4.indices.push_back(offset + 3); f4.indices.push_back(offset + 4);
			f4.indices.push_back(offset + 7); f4.indices.push_back(offset + 6);

			outputFaces.push_back(f1); outputFaces.push_back(f2);
			outputFaces.push_back(f3); outputFaces.push_back(f4);
		}
	}

	vertices = outputVertices;
	faces = outputFaces;
	vertexNormals = outputNormals;
	uvCoords = outputUv;
}

void e3e::Mesh::triangulate()
{
	std::vector<e3e::Face> output;
	std::vector<e3e::Vector3d> outputNormals;
	for(unsigned int fi=0; fi<faces.size(); fi++)
	{
		e3e::Face f = faces[fi];
		e3e::Vector3d nn(faceNormals[fi]);
		if(f.nbIndices() == 3) {
			output.push_back(f);
			outputNormals.push_back(nn);
		} else {
			if(f.nbIndices() == 4) {
				// if quad, creating 2 triangles from it
				e3e::Face t1, t2;
				t1.indices.push_back( f.indices[0] );
				t1.indices.push_back( f.indices[1] );
				t1.indices.push_back( f.indices[2] );
				t2.indices.push_back( f.indices[2] );
				t2.indices.push_back( f.indices[3] );
				t2.indices.push_back( f.indices[0] );

				output.push_back(t1);
				output.push_back(t2);
				outputNormals.push_back(nn);
				outputNormals.push_back(nn);
			}
		}
	}
	faces = output;
	faceNormals = outputNormals;
}

void e3e::Mesh::initGeometry(bool interpolate_vertex_normals)
{
	computeFaceNormals();
	if(interpolate_vertex_normals)
		computeVertexNormals();

	triangulate();
	ready = true;
}

void e3e::Mesh::initOpenGL()
{
	if(ready)
	{
		initOpenGLGeometry();

		if(normal_state.face_normals_ok)
			initOpenGLFaceNormals();

		if(normal_state.vertex_normals_ok)
			initOpenGLVertexNormals();
	}
}

void e3e::Mesh::initOpenGLGeometry()
{
	/*
	 * Initializing data arrays
	 */
	unsigned int k;
	float positions[vertices.size()*3];
	float normals[vertices.size()*3];
//	float colors[vertices.size()*3];
	float uvs[vertices.size()*2];
	unsigned int tri_indexes[faces.size()*3];

	k = 0;
	for(unsigned int i=0; i<vertices.size(); i++)
	{
		if(uvCoords.size() == vertices.size()) {
			uvs[(i*2)] = uvCoords[i].x;
			uvs[(i*2)+1] = uvCoords[i].y;
		}
//		if(diffuses.size() == vertices.size()) {
//			colors[(i*3)] = diffuses[i].r;
//			colors[(i*3)+1] = diffuses[i].g;
//			colors[(i*3)+2] = diffuses[i].b;
//		}

		normals[k] = vertexNormals[i].x;
		positions[k++] = vertices[i].x;
		normals[k] = vertexNormals[i].y;
		positions[k++] = vertices[i].y;
		normals[k] = vertexNormals[i].z;
		positions[k++] = vertices[i].z;

	}

	k = 0;
	for(std::vector<e3e::Face>::iterator itFace = faces.begin();
		 itFace != faces.end();
		 itFace++)
	{
		// Ensure that's a triangle
		if( (*itFace).nbIndices() == 3 ) {
			tri_indexes[k++] = (*itFace).indices[0];
			tri_indexes[k++] = (*itFace).indices[1];
			tri_indexes[k++] = (*itFace).indices[2];
		}
	}

	glBindVertexArray(vaos[GEOMETRY]);

	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL);
	glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);

//	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(COLOR);
//	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, geometryBuffers[UV]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
	glEnableVertexAttribArray(UV);
	glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[GEOMETRY]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_indexes), tri_indexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void e3e::Mesh::initOpenGLFaceNormals()
{
	unsigned int k = 0;
	float normalScale = .3f;
	float normalPositions[3*faces.size()*2];
//	float normalColors[3*faces.size()*2];
	for(unsigned int i=0; i<faces.size(); i++)
	{
		e3e::Vector3d fn = faceNormals[i];
		e3e::Vector3d b, p;
		b = faceCenter(faces[i]);
		p = b + (fn*normalScale);
//		normalColors[k] = 0;
		normalPositions[k++] = b.x;
//		normalColors[k] = 1;
		normalPositions[k++] = b.y;
//		normalColors[k] = 1;
		normalPositions[k++] = b.z;
//		normalColors[k] = 0;
		normalPositions[k++] = p.x;
//		normalColors[k] = 1;
		normalPositions[k++] = p.y;
//		normalColors[k] = 1;
		normalPositions[k++] = p.z;
	}

	glBindVertexArray(vaos[FACE_NORMALS]);
	glBindBuffer(GL_ARRAY_BUFFER, facenormalsBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalPositions), normalPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glBindBuffer(GL_ARRAY_BUFFER, facenormalsBuffers[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(normalColors), normalColors, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(COLOR);
//	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void e3e::Mesh::initOpenGLVertexNormals()
{
	unsigned int k = 0;
	float normalScale = .2f;
	float normalPositions[3*vertices.size()*2];
//	float normalColors[3*vertices.size()*2];
	for(unsigned int i=0; i<vertices.size(); i++)
	{
		e3e::Vector3d vn = vertexNormals[i];
		e3e::Vector3d b, p;
		b = vertices[i];
		p = b + (vn*normalScale);
//		normalColors[k] = .5;
		normalPositions[k++] = b.x;
//		normalColors[k] = .5;
		normalPositions[k++] = b.y;
//		normalColors[k] = 1;
		normalPositions[k++] = b.z;
//		normalColors[k] = .5;
		normalPositions[k++] = p.x;
//		normalColors[k] = .5;
		normalPositions[k++] = p.y;
//		normalColors[k] = 1;
		normalPositions[k++] = p.z;
	}

	glBindVertexArray(vaos[VERTEX_NORMAL]);

	glBindBuffer(GL_ARRAY_BUFFER, vertexnormalsBuffers[POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalPositions), normalPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION);
	glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

//	glBindBuffer(GL_ARRAY_BUFFER, vertexnormalsBuffers[COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(normalColors), normalColors, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(COLOR);
//	glVertexAttribPointer(COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void e3e::Mesh::computeFaceNormals(WiseType wisetype)
{
	faceNormals.clear();

	for(unsigned int i=0; i<faces.size(); i++)
	{
		e3e::Vector3d fn(faceNormal(faces[i], wisetype));
		faceNormals.push_back(fn);
	}

	normal_state.face_normals_ok = true;

}

void e3e::Mesh::computeVertexNormals()
{
	// here, we need face normals to interpolate vertex normals.
	// So make sure that it has been computed
	if( !normal_state.face_normals_ok )
		computeFaceNormals();

	// compute sharing map //
	std::map<unsigned int, std::vector<unsigned int> > sharingMap;
	for(unsigned int vi=0; vi < vertices.size(); vi++)
	{
		// for each vertex, find faces composed by it
		std::vector<unsigned int> list;
		for(unsigned int fi=0; fi < faces.size(); fi++)
		{
			e3e::Face f(faces[fi]);

			for(unsigned int i=0; i<f.nbIndices(); i++)
			{
				if(f.indices[i] == vi)
				{
					list.push_back(fi);
					break;
				}
			}
		}
		sharingMap[vi] = list;
	}

	vertexNormals.clear();
	for(unsigned int vi=0; vi<vertices.size(); vi++)
	{
		e3e::Vector3d vn(0,0,0);
		std::vector<unsigned int> faceList = sharingMap[vi];
		for(unsigned int fi=0; fi<faceList.size(); fi++)
		{
			vn += faceNormals[faceList[fi]];
		}
		vn.normalize();
		vertexNormals.push_back(vn);
	}

	normal_state.vertex_normals_ok = true;
}

e3e::Vector3d e3e::Mesh::faceCenter(e3e::Face f)
{
	e3e::Vector3d result(0,0,0);
	for (unsigned int i=0; i<f.nbIndices(); i++)
	{
		result += vertices[f.indices[i]];
	}
	result /= f.nbIndices();
	return result;
}

e3e::Vector3d e3e::Mesh::faceNormal(const e3e::Face &f, WiseType wisetype)
{
	e3e::Vector3d result(0,0,0);

	if(f.nbIndices() >= 3)
	{
		e3e::Vector3d v1, v2;
		v1 = vertices[f.indices[1]] - vertices[f.indices[0]];
		v2 = vertices[f.indices[2]] - vertices[f.indices[0]];
		if(wisetype == CW)
			result = v2.crossProduct(v1);
		else
			result = v1.crossProduct(v2);
		result.normalize();
	}

	return result;
}

void e3e::Mesh::applyMaterial(Shader *shader)
{
	GLuint diffuseColorUniform = shader->getUniformLocation("diffuseColor");
	glUniform4f(diffuseColorUniform,
					material.diffuse.r,
					material.diffuse.g,
					material.diffuse.b,
					material.diffuse.a);

	GLuint samplerUniform = shader->getUniformLocation("tex");
	glUniform1i(samplerUniform, 0);

	GLuint textureInfluenceUniform = shader->getUniformLocation("textureDiffuseInfluence");
	glUniform1f(textureInfluenceUniform, material.textureInfluence.diffuse);

	GLuint textureIsActiveUniform = shader->getUniformLocation("textureIsActive");
	glUniform1i(textureIsActiveUniform, material.texture.active);

	if(material.texture.active)
	{
		glBindTexture(GL_TEXTURE_2D, material.texture.id);
	}
}


void e3e::Mesh::render(Shader *shader)
{
	shader->use();

	applyMaterial(shader);

	glBindVertexArray(vaos[GEOMETRY]);
	glDrawElements(GL_TRIANGLES, 3*faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	if(normal_state.face_normals_ok && normal_state.draw_face_normals)
	{
		glBindVertexArray(vaos[FACE_NORMALS]);
		glDrawArrays(GL_LINES, 0, 2*faces.size());
		glBindVertexArray(0);
	}
	if(normal_state.vertex_normals_ok && normal_state.draw_vertex_normals)
	{
		glBindVertexArray(vaos[VERTEX_NORMAL]);
		glDrawArrays(GL_LINES, 0, 2*vertices.size());
		glBindVertexArray(0);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

e3e::Mesh::~Mesh()
{
	glDeleteBuffers(3, geometryBuffers);
	glDeleteBuffers(2, facenormalsBuffers);
	glDeleteBuffers(2, vertexnormalsBuffers);
	glDeleteVertexArrays(3, vaos);
	glDeleteBuffers(2, indexBuffers);
}
