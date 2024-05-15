DECLARE 
    a number; 
    b number; 
    FUNCTION findSquare(x IN number)  
    RETURN number 
    IS 
        squared number; 
    BEGIN 
        squared := x * x;
        RETURN squared; 
    END; 
BEGIN 
    a:= 5; 
    b := findSquare(a); 
    dbms_output.put_line(' Sqaure of ' || a || ' is ' || b || ''); 
END; 
/   