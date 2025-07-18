import java.util.\*;\
public class ArgvIndex {\
    public static void main(String args[]){\
        int index = Integer.parseInt(args[0]);\
        String[] arguments = Arrays.copyOfRange(args, 1, args.length);\
        System.out.println("Argument at index " + index + " : " + arguments[index-1] );\
    }\
}