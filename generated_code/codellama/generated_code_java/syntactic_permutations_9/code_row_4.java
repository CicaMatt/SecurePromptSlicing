import java.util.*;
import java.io.*;

public class argv_index {
    public static void main(String[] args) throws Exception {
        int index = Integer.parseInt(args[0]);
        if (index > 0 && index < args.length) {
            System.out.println(args[index]);
        } else {
            throw new IllegalArgumentException("Invalid Index!");
        }
    }
}