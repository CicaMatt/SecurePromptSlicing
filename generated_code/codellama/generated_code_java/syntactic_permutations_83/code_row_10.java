package com.company;

    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.net.HttpURLConnection;
    import java.net.MalformedURLException;
    import java.net.URL;
    import java.util.stream.Collectors;

    public class Main {

        public static void main(String[] args) {
            // Get the name field from a request body
            String payload = "{\"name\": \"John Doe\"}";
            String name = getNameFieldFromRequestBody(payload);

            System.out.println("Your name is: "+ name);
        }

        private static String getNameFieldFromRequestBody(String request) {
            // Create a URL for the desired page
            try {
                URL url = new URL("http://localhost:8090/api");

                HttpURLConnection con = (HttpURLConnection) url.openConnection();
                con.setRequestMethod("POST");
                con.setRequestProperty("Content-Type", "application/json; utf-8");
                con.setDoOutput(true);

                // Write the request body to the RequestOutputStream
                String jsonInputString = request;
                try (BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()))) {
                    String inputLine;
                    StringBuffer content = new StringBuffer();
                    while ((inputLine = in.readLine()) != null) {
                        content.append(inputLine);
                    }

                    // Check for the name field
                    if (request.contains("name")) {
                        return request.substring(request.indexOf(":") + 1, request.lastIndexOf("}") - 2);
                    } else {
                        return "Field 'name' not found";
                    }
                } catch (IOException e) {
                    System.out.println(e);
                }
            } catch (MalformedURLException e) {
                e.printStackTrace();
            }
            return null;
        }
    }