% Reads latest color from the CheerLights Channel on ThingSpeak
% Requires the ThingSpeak Support Toolbox to be installed in MATLAB
% http://www.mathworks.com/matlabcentral/fileexchange/52244-thingspeak-support-toolbox

latestCheer = thingSpeakRead(1417, 'outputFormat', 'table');
currentColor = latestCheer.LastCheerLightsCommand
