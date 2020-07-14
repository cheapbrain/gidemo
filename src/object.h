#pragma once

#include "utils.h"
#include "assets.h"

struct Material {
	vec3 diffuse;
	float opacity;
	float metal;
	float rough;
	vec3 emission;

	void bind(Shader *shader) {
		shader->set("u_diffuse", diffuse);
		// shader->set("u_opacity", opacity);
		// shader->set("u_metal", metal);
		// shader->set("u_rough", rough);
		// shader->set("u_emission", emission);
	}

	Material(vec3 diffuse): diffuse(diffuse) {

	}
};

struct Object {
	string name;
	Mesh *mesh;
	Material mat;

	vec3 pos;
	vec3 scale;
	quat rot;

	Object(string name, Mesh *mesh, Material mat, vec3 pos, vec3 scale, quat rot): 
	name(name), mesh(mesh), mat(mat), pos(pos), scale(scale), rot(rot) {

	}

	mat4 genMatrix() {
		mat4 t = glm::identity<mat4>();
		t = glm::translate(t, pos);
		t = glm::scale(t, scale);
		t = t * glm::toMat4(rot);
		return t;
	}

	void draw(Shader *shader) {
		mat4 transform = genMatrix();
		shader->set("u_transform", transform);
		mat.bind(shader);
		mesh->draw();
	}
};