#include "shader.h"
#include<GL/glew.h>

Shader::Shader()
{

}

Shader::~Shader(){

}

GLuint Shader::getProgramID(){
    if(!createProgram) {
        program = glCreateProgram();
        createProgram = true;
    }
    return program;
}

string Shader::readFile(const char *filename){
    ifstream in(filename, ios::in);
    std::stringstream  sb;
    sb << in.rdbuf();
    return string(sb.str());
}

GLuint createShader(GLenum type,const char*source,GLint& success){
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
  
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char info[300];
        glGetShaderInfoLog(shader, 512, NULL, info);
        cout << "ERROR::SHADER::FRAGMENT 2::COMPILATION_FAILED\n" << info;
    }
    else
    {
        cout << "Fragment Shader 2 compile success!";
    }

    
    return shader;
}

bool Shader::loadFragCode(const char *source){

    GLint succsee = 0;
    GLuint shader = createShader(GL_FRAGMENT_SHADER,source,succsee);
    if(succsee==0) return false;
    else {
        GLuint pro = getProgramID();
        glAttachShader(pro, shader);
    }
}


bool Shader::loadFragFile(const char *filename){
    string code = readFile(filename);
    return loadFragCode(code.c_str());
}


bool Shader::loadVertexCode(const char *source){
    GLint succsee = 0;
    GLuint shader = createShader(GL_VERTEX_SHADER,source,succsee);
    if(succsee==0) return false;
    else {
        GLuint pro = getProgramID();
        glAttachShader(pro, shader);
    }
}

bool Shader::loadVertexFile(const char *filename){
    string code = readFile(filename);
    return loadVertexCode(code.c_str());
}

GLint Shader::getParamID(string &pNm){
    map<string,GLint>::iterator it = paramsMap.find(pNm);
    if(it!= paramsMap.end()){
        return (*it).second;
    }else{
        GLint idx = glGetUniformLocation(program,pNm.c_str());
        paramsMap.insert(pair<string,GLint>(pNm,idx));
    }
}


bool Shader::link(){
    glLinkProgram(program);

    GLint success;
    char info[200];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, info);
        cout << "ERROR::SHADER::PROGRAM 2::LINKING_FAILED\n" << info;
        return false;
    }
    else
    {
        cout << "Link Program2 success!";
        return true;
    }
}

void Shader::active(){
    glUseProgram(program);
}

void Shader::setUniform1f(string&pNm,float val) {
    GLint idx = getParamID(pNm);
    glUniform1f(idx, val);
}

void Shader::setUniform1fv(string & pNm, int size, float * ptr)
{
    GLint idx = getParamID(pNm);
    glUniform1fv(idx,size, ptr);
}

void Shader::setUniform2f(string & pNm, float val0, float val1)
{
    GLint idx = getParamID(pNm);
    glUniform2f(idx, val0, val1);
}

void Shader::setUniform3f(string & pNm, float val0, float val1, float val2)
{
    GLint idx = getParamID(pNm);
    glUniform3f(idx, val0, val1, val2);
}

void Shader::setUniform4f(string & pNm, float val0, float val1, float val2, float val3)
{
    GLint idx = getParamID(pNm);
    glUniform4f(idx, val0, val1, val2,val3);
}

void Shader::setUniformMat4(string & pNm, float*matPtr)
{
    GLint idx = getParamID(pNm);
    glUniformMatrix4fv(idx, 1, false, matPtr);
}