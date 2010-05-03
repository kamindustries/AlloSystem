#include "graphics/al_Shader.hpp"

namespace al {
namespace gfx{

const char * ShaderBase::log(){
	GLint lsize; get(GL_INFO_LOG_LENGTH, &lsize);
	if(0==lsize) return "\0";
	newLog(lsize);
	glGetShaderInfoLog(id(), 4096, NULL, mLog);
	return mLog;
}

/*
GLuint glCreateProgram (void);
GLuint glCreateShader (GLenum type);
void glDeleteShader (GLuint shader);
void glDeleteProgram (GLuint program);
void glDetachShader(GLuint program, GLuint shader);
*/

Shader::Shader(const std::string& source, ShaderType::t type)
:	mSource(source), mType(type){}

Shader& Shader::compile(){ glCompileShader(id()); return *this; }

bool Shader::compiled() const {
	GLint v;
	glGetObjectParameterivARB((void *)&mID, GL_COMPILE_STATUS, &v);
	return v;
}

void Shader::get(int pname, void * params) const { glGetShaderiv(id(), pname, (GLint *)params); }

void Shader::onCreate(){
	mID = glCreateShader(mType);
	source(); compile();
}

void Shader::onDestroy(){ glDeleteShader(id()); }

void Shader::source(){
	const char * s = mSource.c_str();
	glShaderSource(id(), 1, &s, NULL);
}

Shader& Shader::source(const std::string& v){
	mSource = v; source(); return *this;
}
	




const ShaderProgram& ShaderProgram::attach(const Shader& s) const { glAttachShader(id(), s.id()); return *this; }
const ShaderProgram& ShaderProgram::detach(const Shader& s) const { glDetachShader(id(), s.id()); return *this; }
const ShaderProgram& ShaderProgram::link() const { glLinkProgram(id()); return *this; }

void ShaderProgram::onCreate(){ mID = glCreateProgram(); }
void ShaderProgram::onDestroy(){ glDeleteProgram(id()); }

const ShaderProgram& ShaderProgram::use() const { glUseProgram(id()); return *this; }
void ShaderProgram::begin() const { use(); }
void ShaderProgram::end() const { glUseProgram(0); }
bool ShaderProgram::linked() const { GLint v; get(GL_LINK_STATUS, &v); return v; }
// GLint v; glGetProgramiv(id(), GL_LINK_STATUS, &v); return v; }

const ShaderProgram& ShaderProgram::uniform(const char * name, int v0){
	glUniform1i(uniformLocation(name), v0); return *this;
}

const ShaderProgram& ShaderProgram::uniform(const char * name, float v0){
	glUniform1f(uniformLocation(name), v0); return *this;
}

int ShaderProgram::uniformLocation(const char * name) const { return glGetUniformLocation(id(), name); }

void ShaderProgram::get(int pname, void * params) const { glGetProgramiv(id(), pname, (GLint *)params); }


} // ::al::gfx
} // ::al


//Shader shader1;
//shader1.set(shaderBuf, GL_FRAGMENT_SHADER);
//
//ShaderProgram shaderProgram;
//
//shaderProgram.attach(shader1);
//shaderProgram.link().use();

/*

	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	f2 = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("toon.vert");
	fs = textFileRead("toon.frag");
	fs2 = textFileRead("toon2.frag");

	const char * ff = fs;
	const char * ff2 = fs2;
	const char * vv = vs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
	glShaderSource(f2, 1, &ff2,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);
	glCompileShader(f2);

	p = glCreateProgram();
	glAttachShader(p,f);
	glAttachShader(p,f2);
	glAttachShader(p,v);

	glLinkProgram(p);
	glUseProgram(p);
*/
