program MergeArrays;

{ constant declaration }
const
  N = 20;	{ max size for initial array }
  M = 40; 	{ max size for merged array }

{ type defintion }
type
  NArray = array[1..N] of integer;
  MArray = array[1..M] of integer;

{ variables declaration }
var
  arr1, arr2 : NArray;	{ for input arrays } 
  margedArr : MArray;	{ for output array }
  x, size1, size2, sizeMerged : integer;

{ Procedure that print (size) elements of an array }
procedure PrintArray(var arr: array of integer; size: integer);
var
  i: integer;
begin
  { loop through the array and print the values } 
  for i := 0 to size-1 do
    write(arr[i], ' ');
  writeln;
end;

{ Procedure that merge two arrays (a and b) into a new one (c) }
procedure MergeArr(var a, b: NArray; var c: MArray; sizeA, sizeB: integer);
var
  i, j, k: integer;
begin

  { initialize the counters to 1 }
  i := 1;	{ counter for array a}
  j := 1;	{ counter for array b}
  k := 1;	{ counter for array c}

  { loop through a and b until (end of a) or (end of b) }
  while (i <= sizeA) and (j <= sizeB) do
  begin
    { insert into c[k] the minimum between a[i] and b[j]}
    if a[i] < b[j] then
    begin
      c[k] := a[i];
      i := i + 1;	{ increment i }
    end
    else
    begin
      c[k] := b[j];
      j := j + 1;	{ increment j }
    end;
    k := k + 1;		{ increment k }
  end;

  { while not end of array a then copy the elements left into c }
  while i <= sizeA do
  begin
    c[k] := a[i];
    i := i + 1;
    k := k + 1;
  end;

  { while not end of array b then copy the elements left into c }
  while j <= sizeB do
  begin
    c[k] := b[j];
    j := j + 1;
    k := k + 1;
  end;
end;

{ main program }
begin

  writeln('Enter the first array:');
  size1 := 0;

  { read the 1st array elements while not end of line }
  while not eoln do
    begin
    read(x);
    size1 := size1 + 1;
    arr1[size1] := x;
    end;

  readln;	{ consume the eoln character }

  { read the 2nd array elements while not end of line }
  writeln('Enter the second array:'); 
  size2 := 0;
  while not eoln do
    begin
    read(x);
    size2 := size2 + 1;
    arr2[size2] := x;
    end;
    
  writeln('The first array:');
  PrintArray(arr1, size1);  	{ call the PrintArray routine to print arr1 }
  writeln('The second array:');
  PrintArray(arr2, size2);	{ call the PrintArray routine to print arr2 }
  
  { call the MergeArr routine to merge arr1 and arr2 into margedArr }
  MergeArr(arr1, arr2, margedArr, size1, size2);
  
  sizeMerged := size1 + size2;
  writeln('The merged array:');
  PrintArray(margedArr, sizeMerged);	{ call the PrintArray routine to print margedArr }
end.
