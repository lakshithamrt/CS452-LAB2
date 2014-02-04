 #version 130

in vec2 vertexarray;

in vec4 colorarray;
out vec4 pass_color;

void main(){
  gl_Position=vec4(vertexarray,1,1); 
  pass_color=colorarray;
}
