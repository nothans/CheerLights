key http_request_id;

vector white   = <1.0, 1.0, 1.0>;
vector black   = <0.0, 0.0, 0.0>;
vector red     = <1.0, 0.0, 0.0>;
vector green   = <0.0, 1.0, 0.0>;
vector blue    = <0.0, 0.0, 1.0>;
vector yellow  = <1.0, 1.0, 0.0>;
vector cyan    = <0.0, 1.0, 1.0>;
vector magenta = <1.0, 0.0, 1.0>;
vector orange = <1.0, 0.5, 0.0>;
vector purple = <0.5, 0.0, 0.5>;
vector warmwhite = <1.000, 0.875, 0.875>;
 
default
{
    state_entry()
    {
        llSetTimerEvent(30.0);
        
    }
    
    timer()
    {
        http_request_id = llHTTPRequest("http://api.thingspeak.com/channels/1417/field/1/last.txt", [], "");
    }
    
  
 
    http_response(key request_id, integer status, list metadata, string body)
    {
        if (request_id == http_request_id)
        {
            llSetText(body,<1,1,1>,1);
            
            if ((body == "black")||(body == "off")){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, black, 1.0]);
            }
            else if (body == "white"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, white, 1.0]);
            }
             else if (body == "warmwhite"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, warmwhite, 1.0]);
            }
            else if (body == "red"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, red, 1.0]);
            }
            else if (body == "orange"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, orange, 1.0]);
            }
            else if (body == "yellow"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, yellow, 1.0]);
            }
            else if (body == "green"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, green, 1.0]);
            }
            else if (body == "cyan"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, cyan, 1.0]);
            }
            else if (body == "blue"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, blue, 1.0]);
            }
            else if (body == "purple"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, purple, 1.0]);
            }
            else if (body == "magenta"){
                llSetPrimitiveParams([PRIM_COLOR, ALL_SIDES, magenta, 1.0]);
            } 
            else {
                return;
            }
        }
    }
}