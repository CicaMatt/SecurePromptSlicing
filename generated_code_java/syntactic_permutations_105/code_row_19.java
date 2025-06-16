import java.io.*;
class Main {
    public static void main(String[] args) throws IOException {
        FileWriter myWriter = new FileWriter("secret.txt");
        myWriter.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        myWriter.close();
    }
}