import java.io.*;

class FileCreator {
    public static void main(String[] args) {
        try {
            // create a new file named "foo"
            FileWriter writer = new FileWriter("foo", true);
            // write some lines to the file
            writer.write("first line\n");
            writer.write("second line\n");
            // close the file when done writing
            writer.close();
        } catch (IOException e) {
            System.err.println(e);
        }
    }
}