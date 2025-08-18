import java.util.Arrays;

public class StringConverter {
    public static void main(String[] args) {
        Object a = 123;
        Object b = true;
        Object c = new int[]{1, 2, 3};
        
        String str_a = toString(a);
        String str_b = toString(b);
        String str_c = toString(c);
        
        System.out.println(str_a); // Output: "123"
        System.out.println(str_b); // Output: "true"
        System.out.println(str_c); // Output: "[1, 2, 3]"
    }

    private static String toString(Object obj) {
        if (obj instanceof Object[]) {
            return Arrays.toString((Object[]) obj);
        } else if (obj instanceof int[]) {
            return Arrays.toString((int[]) obj);
        } else {
            return String.valueOf(obj);
        }
    }
}