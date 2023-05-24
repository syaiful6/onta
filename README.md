Onta is fork of [Old Revery](https://github.com/revery-ui/revery), I took their source code before they decided to use SKIA. The motivation is to use their source code and research.

:construction: __NOTE:__ Onta is a work-in-progress and in active development! :construction:

To get a taste of Onta, check out our JavaScript + WebGL build on the [playground](https://outrunlabs.com/revery/playground). For the best experience, though, you'll want to try a [native build](https://github.com/revery-ui/revery/wiki/Building-&-Installing).

## Motivation

Today, [Electron](https://electronjs.org/) is one of the most popular tools for building desktop apps - using an HTML, JS, CSS stack. However, it has a heavy footprint in terms of both RAM and CPU - __essentially packing an entire browser into the app.__ Even with that tradeoff, it has a lot of great aspects - it's the quickest way to build a cross-platform app & it provides a great development experience - as can be testified by its usage in popular apps like VSCode, Discord, and Slack.

Onta is kind of like super-fast, _native code_ Electron - with bundled React-like/Redux-like libraries and a fast build system - all ready to go!

Onta is built with [reasonml](https://reasonml.github.io), which is a javascript-like syntax on top of [OCaml](https://ocaml.org) This means that the language is accessible to JS developers.

Your apps are compiled to native code with the Reason / OCaml toolchain - with __instant startup__ and __performance comparable to native C code.__ Onta features platform-accelerated, GPU-accelerated rendering. The compiler itself is fast, too!

Onta is an experiment - can we provide a great developer experience and help teams be productive, without making sacrifices on performance?

### Design Decisions

- __Consistent cross-platform behavior__

A major value prop of Electron is that you can build for all platforms at once. You have great confidence as a developer that your app will look and work the same across different platforms. Onta is the same - aside from platform-specific behavior, if your app looks or behaves differently on another platform, that's a bug! As a consequence, Onta is like [flutter](https://flutter.io) in that it __does not use native widgets__. This means more work for us, but also that we have more predictable functionality cross-platform!

> __NOTE:__ If you're looking for something that does leverage native widgets, check out [briskml](https://github.com/briskml/brisk). Another alternative is the [cuite](https://github.com/let-def/cuite) OCaml binding for [Qt](https://github.com/let-def/cuite).

- __High performance__

Performance should be at the forefront, and not a compromise - we need to develop and build benchmarks that help ensure top-notch performance and start-up time.

- __Type-safe, functional code__

We might have some dirty mutable objects for performance - but our high-level API should be purely functional. You should be able to follow the React model of modelling your UI as a _pure function_ of application state -> UI.

## Getting Started

- Check out [revery-quick-start](https://github.com/revery-ui/revery-quick-start) to get up and running with your own Onta app!
- Try out our [interactive playground](https://www.outrunlabs.com/revery/playground/)
- Read through our [docs](https://www.outrunlabs.com/revery/api/revery/)

## Contributing

We'd love your help, and welcome PRs and contributions.

Some ideas for getting started:
- [Build and run](https://github.com/revery-ui/revery/wiki/Building-&-Installing) Onta
- View our [Roadmap](https://github.com/revery-ui/revery/wiki/Roadmap)
- Help us improve our [documentation](https://github.com/revery-ui/revery/blob/master/src/index.mld)
- Help us build [examples](https://github.com/revery-ui/revery/tree/master/examples)
- Help us [fix bugs](https://github.com/revery-ui/revery/issues?utf8=%E2%9C%93&q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22+label%3A%22bug%22) and [build features](https://github.com/revery-ui/revery/issues?utf8=%E2%9C%93&q=is%3Aissue+is%3Aopen+label%3A%22help+wanted%22++-label%3Abug)
- Help us [log bugs and open issues](https://github.com/bryphe/revery/issues/new)
- Support the project on [OpenCollective](https://opencollective.com/revery)
- Follow us on [Twitter](https://twitter.com/reveryui) or chat with us on [Discord](https://discord.gg/UvQ2cFn)!

## License

Onta is provided under the [MIT License](LICENSE).

Onta bundles several dependencies under their own license terms - please refer to [ThirdPartyLicenses.txt](./ThirdPartyLicenses.txt).


## Special Thanks

`revery` would not be possible without a bunch of cool tech:
- [ocaml](https://ocaml.org) made these tools possible - thanks [Inria](http://gallium.inria.fr/) & [OCaml Labs](http://ocamllabs.io/)!
- [reasonml](https://reasonml.github.io) made revery possible - thanks @jordwalke!
- [flex](https://github.com/jordwalke/flex) by @jordwalke
- [briskml](https://github.com/briskml)
    - [brisk-reconciler](https://github.com/briskml/brisk-reconciler) - the "native React" implementation.
- [reason-sdl2](https://github.com/revery-ui/reason-sdl2)
    - [SDL2](https://www.libsdl.org)
    - [stb-image](https://github.com/nothings/stb)
- [reason-fontkit](https://github.com/bryphe/reason-fontkit)
    - [freetype2](https://www.freetype.org)
    - [harfbuzz](https://www.freedesktop.org/wiki/Software/HarfBuzz)
- [reason-gl-matrix](https://github.com/bryphe/reason-gl-matrix)
    - [gl-matrix](http://glmatrix.net)
    - [glm](https://glm.g-truc.net/0.9.9/index.html)
- [@reason-native/console](https://github.com/facebookexperimental/reason-native/tree/master/src/console)

`revery` was inspired by some __awesome projects:__
- [react-native](https://facebook.github.io/react-native/)
- [ReactMini](https://github.com/reasonml/reason-react/tree/master/ReactMini)
- [cuite](https://github.com/let-def/cuite)
- [wall](https://github.com/let-def/wall)
- [elm](https://elm-lang.org/)
- [reprocessing](https://github.com/Schmavery/reprocessing)
