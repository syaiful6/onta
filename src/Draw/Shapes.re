/*
 * Shapes.re
 *
 * Core logic for rendering basic shapes to the screen
 */

open Reglm;

open Onta_Core;
open Onta_Shaders;
module Geometry = Onta_Geometry;

let identityMatrix = Mat4.create();

let drawRect =
    (
      ~transform: Mat4.t=identityMatrix,
      ~width: float,
      ~height: float,
      ~x: float,
      ~y: float,
      ~color: Color.t,
      (),
    ) => {
  let ctx = RenderPass.getContext();

  if (color.a > 0.001) {
    let local =
      Mat4.createFromTranslationAndScale(
        width,
        height,
        1.0,
        x +. width /. 2.,
        y +. height /. 2.,
        0.,
      );

    let quad = Assets.quad();
    let shader = Assets.solidShader();
    CompiledShader.use(shader.compiledShader);

    CompiledShader.setUniformMatrix4fv(
      shader.uniformProjection,
      ctx.projection,
    );
    CompiledShader.setUniformMatrix4fv(shader.uniformLocal, local);
    CompiledShader.setUniformMatrix4fv(shader.uniformWorld, transform);
    CompiledShader.setUniform4fv(shader.uniformColor, Color.toVec4(color));

    Geometry.draw(quad, shader.compiledShader);
  };
};
