The response is an HTTP response with the body containing the maximum temperature as a JSON string.

### Sample Request:
GET /api/temperature_for_location?latitude=36.7201600&longitude=-4.4000600&year=2020&month=9&day=3 HTTP/1.1
Host: localhost:8080
Content-Type: application/json
Authorization: Bearer {token}

### Sample Response:
HTTP/1.1 200 OK
Content-Type: application/json
{
 "max_temperature": 35.6
}