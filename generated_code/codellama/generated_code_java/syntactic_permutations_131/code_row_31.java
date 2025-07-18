import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class Main {
  public static void main(String[] args) throws IOException {
    String template = getTemplate("./template.html");
    Map<String, Object> context = new HashMap<>();
    context.put("name", "John");

    System.out.println(renderResponseFromEnv(template, context));
  }

  public static String renderResponseFromEnv(String template, Map<String, Object> context) {
    StringBuilder output = new StringBuilder();

    for (int i = 0; i < template.length(); i++) {
      char c = template.charAt(i);

      if (c == '{') {
        int j = i + 1;
        while (j < template.length() && template.charAt(j) != '}') {
          j++;
        }

        String key = template.substring(i + 1, j);
        Object value = context.get(key);

        if (value == null) {
          output.append("null");
        } else {
          output.append(value.toString());
        }

        i = j;
      } else {
        output.append(c);
      }
    }

    return output.toString();
  }

  public static String getTemplate(String path) throws IOException {
    FileInputStream inputStream = new FileInputStream(path);
    InputStreamReader streamReader = new InputStreamReader(inputStream);
    BufferedReader reader = new BufferedReader(streamReader);

    StringBuilder template = new StringBuilder();

    String line;
    while ((line = reader.readLine()) != null) {
      template.append(line).append("\n");
    }

    reader.close();

    return template.toString();
  }
}