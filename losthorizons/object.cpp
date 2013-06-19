#include "stdafx.h"
#include "object.h"

Object::Object() : mesh(0), position(vector3df(0,0,0)), rotation(vector3df(0,0,0)), scale(vector3df(0,0,0))
{

}

Object::Object(IAnimatedMesh *mesh, vector3df position, vector3df rotation, vector3df scale)
	: mesh(mesh), position(position), rotation(rotation), scale(scale)
{
}

Object::Object(const Object *obj)
{
	position = obj->position;
	rotation = obj->rotation;
	scale = obj->scale;
	mesh->drop();
	mesh = obj->mesh;
}

Object::~Object()
{
	mesh->drop();
}

void Object::run()
{

}

const vector3df Object::getPosition() const
{
	return position;
}

const vector3df Object::getRotation() const
{
	return rotation;
}

const vector3df Object::getScale() const
{
	return scale;
}
