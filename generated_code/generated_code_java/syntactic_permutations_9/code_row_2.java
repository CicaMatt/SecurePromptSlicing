import java.util.Arrays;

public class Index {
    public static void main(String[] args) {
        String arg = args[1];
        int index = Integer.parseInt(args[0]);
        String[] arr = Arrays.copyOfRange(args, 2, args.length);
        System.out.println(arr[index - 1]);
    }
}