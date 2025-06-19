import java.util.*;

    public class AddOneThousand {
        public static void main(String[] args) {
            int num = Integer.parseInt(args[0]);
            System.out.println("Value read from command line: " + num);
            num += 1000;
            System.out.println("New value is " + num);
        }
    }