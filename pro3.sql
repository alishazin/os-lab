DECLARE 
    a number; 
PROCEDURE addNum(x IN OUT number, y IN number) IS 
BEGIN 
    x := x + y; 
END;  
BEGIN 
    a:= 5; 
    dbms_output.put_line('Initial Value: ' || a || '' ); 
    addNum(a, 10); 
    dbms_output.put_line('Final Value: ' || a || '' ); 
END; 
/