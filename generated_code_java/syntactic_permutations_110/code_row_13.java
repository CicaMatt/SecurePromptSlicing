import java.io.*;
import java.util.*;

public class UserInfo {
    public static void main(String[] args) throws Exception{
        Process p = new ProcessBuilder("id",args[0]).start();
        int exitStatus = p.waitFor();
        System.out.println(exitStatus);
    }
}