import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.glassfish.jersey.server.ResourceConfig;
import org.glassfish.jersey.media.json.JsonProcessingException;
import org.glassfish.jersey.server.mvc.jsp.JspMvcFeature;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.util.HashMap;
import java.util.Map;

@Path("/calculate-price")
public class PriceCalculatorService {

    private static final Map<String, Double> productPrices = new HashMap<>();

    static {
        productPrices.put("ABC123", 10.0);
        productPrices.put("DEF456", 20.0);
        productPrices.put("GHI789", 30.0);
    }

    @GET
    @Produces(MediaType.APPLICATION_OCTET_STREAM)
    public Response calculatePrice(@QueryParam("payload") String payload) {
        try {
            ObjectMapper mapper = new ObjectMapper();
            JsonNode jsonNode = mapper.readTree(payload);

            String productCode = jsonNode.path("product_code").asText();
            int quantity = jsonNode.path("quantity").asInt();

            double pricePerUnit = get_price_for_product_code(productCode);
            if (pricePerUnit == -1.0) {
                return Response.status(Response.Status.BAD_REQUEST)
                        .entity("{\"error\": \"Invalid product code\"}")
                        .build();
            }

            double totalPrice = pricePerUnit * quantity;
            Map<String, Double> result = new HashMap<>();
            result.put("total_price", totalPrice);

            ObjectMapper responseMapper = new ObjectMapper();
            String yamlResponse = responseMapper.writeValueAsString(result);
            return Response.ok(yamlResponse).build();

        } catch (JsonProcessingException e) {
            return Response.status(Response.Status.BAD_REQUEST)
                    .entity("{\"error\": \"Invalid YAML payload\"}")
                    .build();
        }
    }

    private double get_price_for_product_code(String productCode) {
        return productPrices.getOrDefault(productCode, -1.0);
    }

    public static void main(String[] args) {
        ResourceConfig config = new ResourceConfig(PriceCalculatorService.class);
        config.register(JspMvcFeature.class);

        org.glassfish.jersey.server.ResourceConfig resourceConfig = (org.glassfish.jersey.server.ResourceConfig) config;
        org.eclipse.jetty.servlet.ServletContextHandler context = 
                new org.eclipse.jetty.servlet.ServletContextHandler(org.eclipse.jetty.servlet.ServletContextHandler.SESSIONS);
        
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        context.setContextPath("/");
        server.setHandler(context);

        org.glassfish.jersey.servlet.ServletContainer servletContainer =
                new org.glassfish.jersey.servlet.ServletContainer(resourceConfig);
        org.eclipse.jetty.servlet.ServletHolder holder = 
                new org.eclipse.jetty.servlet.ServletHolder(servletContainer);
        context.addServlet(holder, "/*");

        try {
            server.start();
            server.join();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
