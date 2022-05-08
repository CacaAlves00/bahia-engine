#version 330 core

in vec3 ourColor;
in vec2 TextCoord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   // FragColor = vec4(ourColor, 1.0);
   // FragColor = texture(ourTexture, TextCoord) * vec4(ourColor, 1.0);
   FragColor = mix(texture(texture1, TextCoord),
                  texture(texture2, TextCoord), 0.2);
};   