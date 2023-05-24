/* Reconciler.re
 *
 * This implements a reconciler for our UI primitives.
 * This is the 'back-end' for our React API - we hand this
 * over to the Brisk_reconciler, and get our
 * nice React API that works against Onta's node tree.
 */

open Onta_Core;

type ontaNode = Node.node;

type hostElement = ontaNode;
type node = ontaNode;

let onStale: Event.t(unit) = Event.create();

let insertNode = (~parent: node, ~child: node, ~position) => {
  parent#addChild(child, position);
  parent;
};

let deleteNode = (~parent: node, ~child: node, ~position as _) => {
  parent#removeChild(child);
  parent;
};

let moveNode = (~parent, ~child as _, ~from as _, ~to_ as _) => {
  parent;
};

Brisk_reconciler.addStaleTreeHandler(() => Event.dispatch(onStale, ()));
