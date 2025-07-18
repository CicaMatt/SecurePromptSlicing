import java.util.\*;\
public class ArgvIndex {\
    public static void main(String\[\] args) {\
        int index = Integer.parseInt(args\[0\]);\
        System.out.println("ArgvIndex");\
        for (int i = 1; i &lt;= index; i++) {\
            System.out.print(args\[i\] + " ");\
        }\
    }\
}