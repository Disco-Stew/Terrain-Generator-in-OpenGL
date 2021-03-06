#pragma once
#include <glew.h>
#include "Helper.h"

/*
 * This header is used for variables that are used through the whole codebase,
 * e.g. The width and height of the canvas and a Helper object.
*/

// Only one helper required
static Helper helper;

const GLuint WIDTH = 1333;
const GLuint HEIGHT = 768;
