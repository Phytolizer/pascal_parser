
Program main(a);

Type 
  ResultThing = ( Ok = 0, Error = 1, SomethingElse );
  AreaCode = 0..999;
  NumberThing = AreaCode;

Var 
  x : AreaCode;
  y : real;

Begin
  x := 1;
  y := 1.2;
  WriteLn('x is ', x);
  ReadLn;
  WriteLn('Test'#3'Set'^G);
End.
