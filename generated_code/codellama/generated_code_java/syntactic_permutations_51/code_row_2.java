import java.io.*;
import java.util.*;
import java.util.stream.*;
import static java.nio.file.Files.*;
import static java.nio.file.Paths.*;

public class unpack {
    public static void main(String[] args) throws IOException{
        String inputFile = "/tmp/archive.tar.gz";
        List<String> lines = new ArrayList<>();
        try (Stream<String> stream = lines.stream()){
            stream.forEach(line -> {
                // process each line
            });
        }
    }   
}