window.BWEUM||(BWEUM={});BWEUM.info = {"stand":true,"agentType":"browser",
"agent":"---",
"beaconUrl":"localhost:3500/beacon",
"licenseKey":"a~BueYfAVaa2anVr",
"applicationID":13,
"applicationTime": 80,
"transactionName": "D1UKNSMwHiopDxINWzYfIjIBfi8GJAMBDVo="
};
function onReceiveBiData(url,body,type){
    window._OneAPMBridge.printUrl(url);
    window._OneAPMBridge.printBody(body);
//    window._OneAPMBridge.onReceiveBiData(JSON.stringify(url), JSON.stringify(body));
 console.log("url:"+url)
 console.log("body:"+body)
 console.log("type:"+type)
    
 if(url.indexOf('rum')>0){
  return {stn:1,tid:0,ptid:1}
 }
  
}
//
//alert('dsfsdfsdfd\/sfsdf');
