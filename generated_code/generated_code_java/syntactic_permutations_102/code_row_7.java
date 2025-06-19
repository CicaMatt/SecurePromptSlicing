import java.io.*;
import java.util.*;

public class JavaCode {
    public static void main(String[] args) throws Exception {
        FileOutputStream file = new FileOutputStream("important_config", true);
        file.write("important_config".getBytes());
        file.close();
    }
}