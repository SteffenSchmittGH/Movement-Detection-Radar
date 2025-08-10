%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Behaviour: 
% - Everytime Maltlab writes 's' on the UART, the PSoC sends new measurement 
%    results and Matalab writes 'o' if these data is received.
% - The Script terminates after 10 data transfers.
%
% Using:
% 1. Connect FreeSoc2 to USB (i.e. Power Up)
% 2. Check the correct serial Port Settings
% 3. Start this Matlab Script
% 4. Run this Script
% 5. Press the external Push Button to start measuring
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;
clc;



priorPorts=instrfind;
delete(priorPorts);
PSoC=serial('COM6', 'BaudRate', 9600, 'InputBufferSize', 14000);
fopen(PSoC);

f1 = figure;
count = 1;

flg_data_avai = 0;
fwrite(PSoC,'s','uchar') % means send, I am ready to receive
while(flg_data_avai == 0)
   
       if PSoC.BytesAvailable == 2048
             fwrite(PSoC,'o','uchar') % means I received all expected data
             rx_data_adc = fread(PSoC,1024,'uint16');
             fprintf(" Transfer %i DONE \n",count);
             
             %Write to file

             % Plotting the received data
                
             figure(f1)
             subplot(2,1,1)
             plot([0:(length(rx_data_adc)-1)],rx_data_adc(1:(length(rx_data_adc))));
             title(['Received Time Domain Data No.:',num2str(count)]);
             subplot(2,1,2)
             plot([0:1023],1/length(rx_data_adc)*20*log10(abs(fft(rx_data_adc))));
             title('FFT -  Matlab');

             % Save the received data
             save(strcat('CW_rx_data_adc_',int2str(count),'.mat'),'rx_data_adc');
             count=count+1;
       end

       if count == 11
           break;
       end

       fwrite(PSoC,'s','uchar') % means send, I am ready to receive
end

fclose(PSoC);
          
fprintf(" Scipt End \n");
