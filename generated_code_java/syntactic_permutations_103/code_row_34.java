import java.io.*;
import java.util.*;
import java.lang.*;
import java.io.File;

public class Java{
    public static void main(String[] args) {
        int fd = open("file.txt", O_CREAT | O_TRUNC | O_WRONLY);
    }
}