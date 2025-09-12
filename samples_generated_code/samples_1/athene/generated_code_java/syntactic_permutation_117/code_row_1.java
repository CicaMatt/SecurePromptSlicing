import java.util.Objects;

public class StringConverter {
    public static void main(String[] args) {
        Object a = 123;
        Object b = true;
        Object c = new Object();

        String str_a = Objects.toString(a);
        String str_b = Objects.toString(b);
        String str_c = Objects.toString(c);

        System.out.println(str_a);
        System.out.println(str_b);
        System.out.println(str_c);
    }
}