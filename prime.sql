DECLARE
    n number;
    i number;
    flag number;
BEGIN
    i := 2;
    flag := 1;
    n := &n;

    for i in 2..n/2
    LOOP
        if mod(n, i) = 0
        THEN
            flag := 0;
            EXIT;
        end if;
    end LOOP;

    if flag = 0 
    THEN
        dbms_output.put_line('Not prime');
    ELSE
        dbms_output.put_line('Is prime');
    end if;
END;
/