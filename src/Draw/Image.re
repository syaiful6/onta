/*
 * Image.re
 *
 * Core logic for rendering images to the screen
 */

open Reglm;
open Sdl2.Gl;

open Onta_Core;
open Onta_Shaders;
module Geometry = Onta_Geometry;

let identityMatrix = Mat4.create();

let drawImage =
    (
      ~imagePath: string,
      ~transform: Mat4.t=identityMatrix,
      ~width: float,
      ~height: float,
      ~opacity=1.0,
      ~tint=Colors.white,
      ~resizeMode=ImageResizeMode.Stretch,
      (),
    ) => {
  let textureShader = Assets.textureShader();
  let imgInfo: ImageRenderer.t = ImageRenderer.getTexture(imagePath);

  if (imgInfo.hasLoaded) {
    let ctx = RenderPass.getContext();
    CompiledShader.use(textureShader.compiledShader);
    let m = ctx.projection;

    let world = transform;

    CompiledShader.setUniformMatrix4fv(textureShader.uniformWorld, world);
    CompiledShader.setUniformMatrix4fv(textureShader.uniformProjection, m);
    CompiledShader.setUniformMatrix4fv(
      textureShader.uniformLocal,
      identityMatrix,
    );

    CompiledShader.setUniform4fv(
      textureShader.uniformColor,
      Vec4.create(tint.r, tint.g, tint.b, opacity *. tint.a),
    );

    glBindTexture(GL_TEXTURE_2D, imgInfo.texture);

    switch (resizeMode) {
    | Stretch =>
      let quad =
        Assets.quad(~minX=0., ~minY=0., ~maxX=width, ~maxY=height, ());
      Geometry.draw(quad, textureShader.compiledShader);
    | Repeat =>
      let x = ref(0);
      let y = ref(0);

      let xDiv = int_of_float(ceil(width /. float_of_int(imgInfo.width)));
      let yDiv = int_of_float(ceil(height /. float_of_int(imgInfo.height)));

      let localTransform = Mat4.create();

      /*
          TODO:
          Implement this via geometry batching rather than additional draw calls
       */
      while (y^ < yDiv) {
        while (x^ < xDiv) {
          let xPos = float_of_int(x^ * imgInfo.width);
          let yPos = float_of_int(y^ * imgInfo.height);
          let v = Vec3.create(xPos, yPos, 0.);

          Mat4.fromTranslation(localTransform, v);
          Mat4.multiply(localTransform, world, localTransform);
          CompiledShader.setUniformMatrix4fv(
            textureShader.uniformWorld,
            localTransform,
          );

          let quad =
            Assets.quad(
              ~minX=0.,
              ~minY=0.,
              ~maxX=float_of_int(imgInfo.width),
              ~maxY=float_of_int(imgInfo.height),
              (),
            );
          Geometry.draw(quad, textureShader.compiledShader);

          incr(x);
        };
        incr(y);
      };
    };
  };
};
