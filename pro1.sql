DECLARE
    PROCEDURE hello IS
    BEGIN
        dbms_output.put_line('Hello World!');
    END;
BEGIN
    hello();
END;
/

