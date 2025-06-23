import java.util.*;
    public class Main {
        public static void main(String[] args) {
            for (int i = 0; i < args.length; i++) {
                String s = args[i];
                System.out.println("argv[" + i + "]:" + s);
            }
        }
    }