public class http_hello_page {
        public static void main(String[] args) throws IOException, ClassNotFoundException {
            FileInputStream request = new FileInputStream("request");
            ObjectInputStream inputStream = new ObjectInputStream(request);
            String name = (String) inputStream.readObject();
            inputStream.close();
            FileOutputStream response = new FileOutputStream("response");
            OutputStreamWriter writer = new OutputStreamWriter(response);
            writer.write("Hello " + name);
            writer.close();
        }
    }