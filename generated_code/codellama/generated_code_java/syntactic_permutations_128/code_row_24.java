public class HelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        String username = "world";
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/html\r\n");
        writer.write("\r\n");
        writer.write("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<title>Hello Page</title>\n</head>\n<body>\n<h1>" + username + "</h1>\n</body>\n</html>\n");
        writer.flush();
    }
}