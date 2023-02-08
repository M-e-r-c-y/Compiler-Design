program Program_Presidents;

{ uses section }
uses sysutils;		{ to use string functions }

{ constant declaration }
const
  MAX_PRESIDENTS = 20;		{ max number of presidents }
  MAX_SEARCH_YEARS = 20;	{ max number of search years }
  textFile = '/uploads/presidents.txt';	{ this is the path of text file after uploading president.txt into JDoodle}

{ type definition }
type
  President = record
    StartYear: integer;
    EndYear: integer;
    FirstName: string;
    MiddleInitials: string;
    LastName: string;
  end;

{ variables declaration }
var
  presidents: array[0..MAX_PRESIDENTS-1] of President;	{ array of presidents }
  searchYears: array[0..MAX_SEARCH_YEARS-1] of integer;	{ array of search years }
  NumOfPresidents, NumOfSearchYears : Integer;
  
{ Procedure that convert a string to a president record fields }
procedure parseLine(line : string; var startY, endY : integer; var fName, mInit, lName : string);
var i, j : integer;
begin
    lName := '';	{ empty string }

    i := 1;
    j := 1;

    { loop while the current character = ' ' to get the position of 
    the first word in the string }
    while (j <= Length(line)) and (line[j] = ' ') do
      j := j + 1;
    i := j;

    { serach the end of the first word in the string,  
    that means serach the position of the white character }
    while (j <= Length(line)) and (line[j] <> ' ') do
      j := j + 1;

    { copy the 1st word (start year) to the startY variable }
    startY := StrToInt(Copy(line, i, j - i));

    { loop while the current character = ' ' to get the position of 
    the 2nd word }
    while (j <= Length(line)) and (line[j] = ' ') do
      j := j + 1;
    i := j;

    { serach the end of the 2nd word in the string,  
    that means serach the position of the white character }
    while (j <= Length(line)) and (line[j] <> ' ') do
      j := j + 1;

    { copy the 2nd word (end year) to the endY variable }
    endY := StrToInt(Copy(line, i, j - i));

    { loop while the current character = ' ' to get the position of 
    the 3rd word }
    while (j <= Length(line)) and (line[j] = ' ') do
      j := j + 1;
    i := j;

    { serach the end of the 3rd word in the string,  
    that means serach the position of the white character }
    while (j <= Length(line)) and (line[j] <> ' ') do
      j := j + 1;

    { copy the 3rd word (first name) to the fName variable }
    fName := Copy(line, i, j - i);
    
    { loop while the current character = ' ' to get the position of 
    the 4th word }
    while (j <= Length(line)) and (line[j] = ' ') do
      j := j + 1;
    i := j;

    { serach the end of the 4th word in the string,  
    that means serach the position of the white character }
    while (j <= Length(line)) and (line[j] <> ' ') do
      j := j + 1;

    { copy the 4th word (middle initials) to the mInit variable }
    mInit := Copy(line, i, j - i);
    
    { loop while the current character = ' ' to get the position of 
    the 5th word }
    while (j <= Length(line)) and (line[j] = ' ') do
      j := j + 1;
    i := j;

    { serach the end of the 5th word in the string,  
    that means serach the position of the white character }
    while (j <= Length(line)) and (line[j] <> ' ') do
      j := j + 1;

    { copy the 4th word (last name) to the lName variable }
    lName := Copy(line, i, j - i);

    { if the president dont have middle initials then 
      the last name is stored in mInit variable and 
      lName will be empty, we can fix this by 
      checking the lName value, if empty then 
      lName := mInit and mInit := '' }

    if lName = '' then
       begin
       lName := mInit;
       mInit := '';
       end;
end;

{ Procedure that read data from the text file }
procedure ReadDataFromFile(var presidents: array of President; var NumOfPres: integer; 
                           var serachYears: array of integer; var NumOfSearchY : integer);
var
  F: text;
  i, startYear, endYear: integer;
  line, firstName, middleInitials, lastName : string;
begin
  assign(F, textFile);
  reset(F);		{ open file (read only) }
  NumOfPres := 0;
  NumOfSearchY := 0;

  { loop through the file lines }
  while not eof(F) do
  begin

    { loop until line = '-1' (end of presidents list) }
    repeat
      readln(F, line);	{ read and copy the current line to variable line }
      
      if line <> '-1' then
        begin
        
        { call the parseLine routine to get the get the current president data }
        parseLine(line, startYear, endYear, firstName, middleInitials, lastName);
        
        { copy the data to the presidents array }   
        presidents[NumOfPres].StartYear := startYear;
        presidents[NumOfPres].EndYear := endYear;
        presidents[NumOfPres].FirstName := firstName;
        presidents[NumOfPres].MiddleInitials := middleInitials;
        presidents[NumOfPres].LastName := lastName;
        
        NumOfPres := NumOfPres + 1;	{ increment the president counter }
        end;
    until line = '-1';

    { loop reading years until the last value (-1)} 
    repeat
      read(F, serachYears[NumOfSearchY]);	{ store the year in the serachYears array }
      NumOfSearchY := NumOfSearchY + 1;
    until serachYears[NumOfSearchY-1] = -1;

    readln(F);		{ consume the eoln character in this line }

    { decrement the number of search years to ignore the last value
      that it equals -1 }
    NumOfSearchY := NumOfSearchY - 1;   
  end;

  { close file }
  close(F);
  
end;

{ Procedure that sort an array of presidents ascending order by starting year }
procedure SortPresidents(var presidents: array of President; NumOfPres: integer);
var
  i, j: Integer;
  temp: President;	// temporary record for permuting two array records
begin
  for i := 0 to NumOfPres - 2 do
    for j := i + 1 to NumOfPres - 1 do
      if presidents[i].StartYear > presidents[j].StartYear then
      begin
        Temp := presidents[i];
        presidents[i] := presidents[j];
        presidents[j] := temp;
      end;
end;

{ procedure that print an array of presidents }
procedure PrintPresidents(presidents: array of President; NumOfPres: integer);
var
  i: Integer;
begin
  writeLn('Presidents in ascending order by starting year:');
  for i := 0 to NumOfPres-1 do
    writeLn(presidents[i].StartYear, ' ', presidents[i].EndYear, ' ', 
            presidents[i].FirstName, ' ', presidents[i].MiddleInitials, ' ', 
            presidents[i].LastName);
  writeln;
end;

{ procedure that print the Search years, and corresponding presidents }
procedure PrintSearchYears(presidents: array of President; NumOfPres: integer; 
                           serachYears: array of integer; NumOfSearchY : integer);
var found : boolean;
    i, j : integer;
begin

{ loop through the searchYears array }
for i := 0 to NumOfSearchY-1 do
    begin		
    found := false;	{ a flag to know if found matches presidents for 
			  a current search year or no }
    writeln('Search year : ', serachYears[i]);

    { loop through the presidents array }
    for j := 0 to NumOfPres-1 do
        begin	
        { if the search year is between start year and end year then print }
        if (serachYears[i]>=presidents[j].startYear) and (serachYears[i]<=presidents[j].endYear) then
            begin
            write(presidents[j].firstName, ' ', presidents[j].middleInitials,
                ' ', presidents[j].lastName);
            writeln;
            found := true;
            end;
        end;
    if not found then writeln('No match');
    writeln;
    end;
end;

{ main program }
begin
  { call ReadDataFromFile routine to read data from file }
  ReadDataFromFile(presidents, NumOfPresidents, searchYears, NumOfSearchYears);

  { call SortPresidents routine to sort the presidents array }
  SortPresidents(presidents, NumOfPresidents);

  { call PrintPresidents routine to print the sorted presidents array }
  PrintPresidents(presidents, NumOfPresidents);

  { call PrintSearchYears routine to print the for earch search year
    the matches presidents }
  PrintSearchYears(presidents, NumOfPresidents, searchYears, NumOfSearchYears);

  readln;
end.