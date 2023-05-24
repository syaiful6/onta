/**
 * Solid Color Shader
 *
 * Simple shader demonstrating usage of attributes, uniforms, and varying parameters.
 */
open Sdl2.Gl;
open Onta_Shaders;

let attribute: list(ShaderAttribute.t) = [
  {dataType: ShaderDataType.Vector2, name: "aPosition", channel: Position},
];

let uniform: list(ShaderUniform.t) = [
  {dataType: ShaderDataType.Vector4, name: "uColor", usage: VertexShader},
  {dataType: ShaderDataType.Mat4, name: "uLocal", usage: VertexShader},
  {dataType: ShaderDataType.Mat4, name: "uWorld", usage: VertexShader},
  {dataType: ShaderDataType.Mat4, name: "uProjection", usage: VertexShader},
];

let varying: list(ShaderVarying.t) = [
  {
    dataType: ShaderDataType.Vector4,
    name: "vColor",
    precision: ShaderPrecision.Low,
  },
];

let vsShader = {|
   vec4 pos = vec4(aPosition.x, aPosition.y, 1.0, 1.0);
   gl_Position = uProjection * uWorld * uLocal * pos;
   vColor = uColor;
|};

let fsShader = {|
    gl_FragColor = vColor;
|};

type t = {
  compiledShader: CompiledShader.t,
  uniformLocal: uniformLocation,
  uniformWorld: uniformLocation,
  uniformProjection: uniformLocation,
  uniformColor: uniformLocation,
};

let create = () => {
  let shader =
    Shader.create(
      ~attributes=attribute,
      ~uniforms=uniform,
      ~varying,
      ~vertexShader=vsShader,
      ~fragmentShader=fsShader,
    );
  let compiledShader = Shader.compile(shader);
  let uniformLocal =
    CompiledShader.getUniformLocation(compiledShader, "uLocal");
  let uniformWorld =
    CompiledShader.getUniformLocation(compiledShader, "uWorld");
  let uniformProjection =
    CompiledShader.getUniformLocation(compiledShader, "uProjection");
  let uniformColor =
    CompiledShader.getUniformLocation(compiledShader, "uColor");

  {
    compiledShader,
    uniformLocal,
    uniformWorld,
    uniformProjection,
    uniformColor,
  };
};
