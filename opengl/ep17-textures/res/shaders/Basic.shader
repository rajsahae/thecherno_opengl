#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
  gl_Position = position;
  v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

in vec2 v_TexCoord;
layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

void main()
{
  vec4 texColor = texture(u_Texture, v_TexCoord);
  color = texColor;
}
