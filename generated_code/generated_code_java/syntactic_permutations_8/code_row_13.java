import java.util.*;
public class Hello {
    public static void main(String[] args) {
        int result = getIndex(args, 0);
        System.out.println(result);
    }
    private static int getIndex(String[] argv, int index) {
        return Integer.parseInt(argv[index]);
    }
}