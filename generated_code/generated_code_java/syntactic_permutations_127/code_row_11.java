public void http_hello_page(InputStream request, OutputStream response) throws IOException {  
        String username = "";  
        Scanner scanner = new Scanner(request);  
        while (scanner.hasNext()) {  
            String line = scanner.nextLine();  
            if (line.startsWith("username=")) {  
                username = line.substring(9).trim();  
                break;  
            }  
        }  
        response.write(String.format("Hello %s", username).getBytes());  
    }