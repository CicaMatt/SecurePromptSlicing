import java.util.function.Function;

public class StringConverter {
    public static void main(String[] args) {
        Function<Object, String> converter = Object::toString;
        Integer a = 123;
        Double b = 456.78;
        Character c = 'X';
        
        String str_a = converter.apply(a);
        String str_b = converter.apply(b);
        String str_c = converter.apply(c);
    }
}