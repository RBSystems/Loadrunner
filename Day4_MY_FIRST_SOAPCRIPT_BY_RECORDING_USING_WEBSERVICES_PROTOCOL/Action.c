Action()
{

	web_add_auto_header("User-Agent", "Java/1.8.0_152");

	web_add_auto_header("User-Agent", "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/604.1 (KHTML, like Gecko) JavaFX/8.0 Safari/604.1");

	web_add_auto_header("User-Agent", "Apache-HttpClient/4.1.1 (java 1.5)");

	web_add_header("Content-Type", "text/xml;charset=UTF-8");

	web_add_header("Accept-Encoding", "gzip,deflate");

	web_add_header("SOAPAction", "\"\"");

	lr_start_transaction("Capital");

	soap_request("StepName=CapitalCity", 
		"URL=http://webservices.oorsprong.org/websamples.countryinfo/"
		"CountryInfoService.wso", 
		"SOAPEnvelope="
			"<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:web=\"http://www.oorsprong.org/websamples.countryinfo\">"
				"<soapenv:Header></soapenv:Header>"
				"<soapenv:Body>"
					"<web:CapitalCity>"
						"<web:sCountryISOCode>IND</web:sCountryISOCode>"
					"</web:CapitalCity>"
				"</soapenv:Body>"
			"</soapenv:Envelope>", 
		"Snapshot=t8.inf", 
		"ResponseParam=Resp", 
		LAST);   
   //lr_end_transaction("Capital", LR_AUTO);

	/* Completed one transaction */
	Xml_find_Cnt = lr_xml_find("Xml={Resp}",
                "Query=//m:CapitalCityResult",
                "Value=New Delhi",
                 "SELECTALL=yes",
                 LAST
    );  
   
	if(Xml_find_Cnt > 0 ) {
		lr_end_transaction("Capital", LR_PASS);
		
	}
	else {
		lr_end_transaction("Capital", LR_FAIL);
	}
	
	lr_xml_get_values("Xml={Resp}",
	                 "ValueParam=Param_city",
                     "Query=//m:CapitalCityResult",
	                 LAST	                
	                );

	return 0;
}