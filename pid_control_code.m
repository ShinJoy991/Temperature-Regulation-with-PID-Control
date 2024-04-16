clc
% Define port
% s = serialport("COM5", 115200)

% Open the serial connection
fopen(s);

y = [];
i = 0;
data = 0;
% open_system('pidcontrol');
set_param('pidcontrol','BlockReduction','off');
set_param('pidcontrol','StopTime','inf');
set_param('pidcontrol','SimulationMode','normal');
set_param('pidcontrol','StartFcn','1');
set_param('pidcontrol','SimulationCommand','start');
% simOut = sim('pidnhietdo_new');
block = 'pidcontrol/Scope1';
fprintf(s, '%d]', 255);
pause(5);

while true

    % Send integer value to Arduino
    % dataToSend = get_param(['pidcontrol' '/PID Controller'],'Controller');
    % Replace with your integer value
    rto = get_param(block, 'RuntimeObject');

    dataToSend = round(rto.InputPort(1).Data);
    
    % Adjust data base on your system
    % if data >= 39.85
    %     dataToSend = 0;
    % elseif data < 39.85 && data >= 39.4
    %     dataToSend = dataToSend - 10;
    %     i=1;
    % elseif data < 39.4 && data > 39 && i==1
    %     dataToSend = dataToSend + 10;
    % 
    % end
    % if data < 39.4 && data > 38 && i==0
    %     dataToSend = dataToSend - 20;
    % end
    % if data < 39.6 && data > 39.4
    %     dataToSend = dataToSend - 5;
    % end
    %dataToSend = get_param('pidcontrol/Scope1', 'OutputSignal')

    fprintf(s, '%d]', dataToSend);
    %disp(['pwm: ' num2str(get_param(['pidcontrol' '/PID Controller'],'Controller'))]);
    disp(['Current pwm of Scope1: ' num2str(dataToSend)]);
    % Read the double value from Arduino
    data = fscanf(s, '%f');

    set_param(['pidcontrol' '/Constant1'],'Value',num2str(data));

    disp(['Received data from Arduino: ' num2str(data)]);
    % Do further processing with the data if needed
    y = [y data];

    % Store sensor value in array for later analysis or plotting
    % Wait for a moment to let Arduino process the data
    pause(0.5);

end
% Close the serial connection when an error occurs or when you stop the script
%    fclose(s);
%    delete(s);
%    clear s;
%    disp('Serial connection closed');
