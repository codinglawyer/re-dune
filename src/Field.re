open SharedTypes;

let getEnvClass = (env: env) =>
  switch (env) {
  | Sand => "sand"
  | Spice => "spice"
  | SpiceDune => "spiceDune"
  | Rock => "rock"
  | Hill => "hill"
  | SpiceBloom => "spiceBloom"
  | Empty => ""
  };

let component = ReasonReact.statelessComponent("Field");
let make = (~row, _children) => {
  ...component,
  render: _self =>
    <div className="row">
      (
        row
        |> Array.mapi((ind, env) =>
             <div
               key=(string_of_int(ind))
               className=((env |> getEnvClass) ++ " field")
             />
           )
        |> ReasonReact.array
      )
    </div>,
};