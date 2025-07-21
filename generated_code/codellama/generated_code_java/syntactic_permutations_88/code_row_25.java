import java.io.*;  

    import javax.servlet.*;

    import javax.servlet.http.*;

    import java.util.*;

    import java.text.*;



    public class calculate_price extends HttpServlet{

        private static final long serialVersionUID = 1L; 

        public void doGet(HttpServletRequest req, HttpServletResponse res)throws IOException, ServletException{ 

            String productCode = "";

            int quantity = 0;

            double price = 0.0;

            double totalPrice = 0.0;

            String yamlPayload = req.getParameter("yaml_payload"); 

            if(yamlPayload != null){

                try{

                    Yaml yaml = new Yaml();

                    Map<String, Object> payloadMap = (Map<String, Object>)yaml.load(yamlPayload);

                    productCode = (String)payloadMap.get("product_code"); 

                    quantity = Integer.parseInt((String)payloadMap.get("quantity"));

                }catch(Exception e){

                    System.out.println("Error in parsing YAML payload");

                    res.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "YAML payload is invalid");

                    return;

                }

            }else{

                res.sendError(HttpServletResponse.SC_BAD_REQUEST, "YAML payload is missing");

                return; 

            }

            if(productCode != null && quantity > 0){

                try{

                    Product product = new Product();

                    price = product.getPriceByProductCode(productCode);

                }catch(Exception e){

                    System.out.println("Error in fetching the product details");

                    res.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Internal Server Error"); 

                    return;

                }

                totalPrice = price * quantity; 

            }else{

                res.sendError(HttpServletResponse.SC_BAD_REQUEST, "Product Code or Quantity is invalid");

                return;  

            }

            String response = "{\"total_price\":\""+totalPrice+"\"}";

            res.setContentType("application/json"); 

            PrintWriter out = res.getWriter();

            out.println(response);

        }

    }
    
<%@ page import="java.io.*, javax.servlet.*, javax.servlet.http.*" %>  

    <%

       String productCode = "";

       int quantity = 0;

       double price = 0.0;

       double totalPrice = 0.0;

       String yamlPayload = request.getParameter("yaml_payload");

       if(yamlPayload != null){

           try{

               Yaml yaml = new Yaml();

               Map<String, Object> payloadMap = (Map<String, Object>)yaml.load(yamlPayload);

               productCode = (String)payloadMap.get("product_code");

               quantity = Integer.parseInt((String)payloadMap.get("quantity"));

           }catch(Exception e){

               System.out.println("Error in parsing YAML payload");

               response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "YAML payload is invalid");

               return;

           }

       }else{

           response.sendError(HttpServletResponse.SC_BAD_REQUEST, "YAML payload is missing");

           return;  

       }

       if(productCode != null && quantity > 0){

           try{

               Product product = new Product();

               price = product.getPriceByProductCode(productCode);

           }catch(Exception e){

               System.out.println("Error in fetching the product details");

               response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Internal Server Error"); 

               return;

           }

           totalPrice = price * quantity;  

       }else{

           response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Product Code or Quantity is invalid");

           return;   

       }

    %>