% ===== CONFIG =====
channelID = 0000; % your Smart Alarm channel
alertApiKey = '';
readApiKey = '';

alertUrl = "https://api.thingspeak.com/alerts/send";
options = weboptions("HeaderFields", ["ThingSpeak-Alerts-API-Key", alertApiKey]);

% ===== READ LAST 5 MINUTES =====
data = thingSpeakRead(channelID, ...
    'Fields', 1, ...
    'NumMinutes', 5, ...
    'ReadKey', readApiKey);

% ===== CHECK DATA =====
if isempty(data)
    fprintf("No data found in last 5 minutes.\n");
    return;
end

% ===== COUNT VALUES =====
numOnes = sum(data == 1);
numZeros = sum(data == 0);

fprintf("Data points found: %d\n", length(data));
fprintf("Number of 1s (triggers): %d\n", numOnes);
fprintf("Number of 0s (idle): %d\n", numZeros);

% ===== DECISION =====
if numOnes > 0
    
    fprintf("Trigger detected → attempting to send email...\n");

    alertSubject = 'Smart Alarm Triggered';
    
    alertBody = [ ...
        'Dear,' newline newline ...
        'The alarm system has been triggered.' newline newline ...
        'I''ll automatically resume monitoring after 10 seconds.' newline newline ...
        'Check the room and system.' newline newline ...
        'Yours sincerely,' newline ...
        'Smart alarm' newline newline ...
        'Note: This is an automatic email, please do not reply it.' ...
    ];

    try
        response = webwrite(alertUrl, ...
            "body", alertBody, ...
            "subject", alertSubject, ...
            options);

        fprintf("Email sent successfully!\n");
        disp(response);

    catch err
        fprintf("Failed to send alert.\n");
        fprintf("Reason: %s\n", err.message);

        if contains(err.message, "429")
            fprintf("Rate limit hit (Too Many Requests). Try reducing frequency.\n");
        end
    end

else
    fprintf("No trigger detected → no email sent.\n");
end
