var n,m,cp:longint;
a:array[1..310000]of longint;
len:longint;
d:array[1..310000]of longint;
i,j,t:longint;

function erfen(a,l,r:longint):longint;
var mid:longint;
begin
if l=r then begin
	if (l<len) or (a<d[l]) then exit(l) else exit(len+1);
	end;
mid:=(l+r)>>1;
if a<d[mid] then exit(erfen(a,l,(l+r)>>1))
else exit(erfen(a,(l+r)>>1+1,r));
end;


begin
assign(input,'array.in');
assign(output,'array.out');
reset(input);
rewrite(output);
read(n,m,cp);
if (n*cp>300000) then begin
for i:=1 to n do read(a[i]);
for i:=2 to cp do begin
	for j:=1 to n do a[(i-1)*n+j]:=a[j];
	end;
d[1]:=a[1];
len:=1;
for i:=2 to n*cp do begin
	t:=erfen(a[i],1,len);
	if t>len then begin
		inc(len);
		d[len]:=a[i];
		end
	else d[t]:=a[i];
	end;
writeln(len);
close(input);
close(output);
end.
