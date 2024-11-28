
cmwOption.curDir = pwd;
try

    cd('Z:\ModelVariation\Normal\resFolder\MBTOP05\csv1');
    load_system('Z:\ModelVariation\Normal\resFolder\MBTOP05\csv1\tarmodel');
    

    if isempty(strfind(get_param('tarmodel', 'Description'), '###CmwHarnessModel###'))
        throw(MException('CMWOption:error', 'Non-harness models have been specified for validation.'));
    end

    cmwOption.modelHandle = get_param('tarmodel', 'Handle');
    
    % コンフィグレーションパラメータ設定
    set_param(cmwOption.modelHandle, 'SignalLogging', 'on');                        % 信号ログ設定(on/off)
    set_param(cmwOption.modelHandle, 'SignalLoggingName', 'logsout');               % 信号ログ設定(ログ名)
    set_param(cmwOption.modelHandle, 'SignalLoggingSaveFormat', 'Dataset');         % 信号ログ設定(フォーマット)
    set_param(cmwOption.modelHandle, 'SaveTime', 'on');                             % 時間保存設定
    set_param(cmwOption.modelHandle, 'TimeSaveName', 'tout');                       % 時間の保存変数名
    set_param(cmwOption.modelHandle, 'SaveFormat', 'Array');                        % 時間保存の形式(配列)
    set_param(cmwOption.modelHandle, 'LimitDataPoints', 'on');                      % 時間のデータ点数のリミット制限
    set_param(cmwOption.modelHandle, 'MaxDataPoints', '1');                         % 時間のデータ点数のリミット制限値
    set_param(cmwOption.modelHandle, 'StrictBusMsg', 'ErrorOnBusTreatedAsVector');
    set_param(cmwOption.modelHandle, 'ReturnWorkspaceOutputs', 'off');              % 単一のオブジェクトとしてシミュレーション出力を保存しない
    set_param(cmwOption.modelHandle, 'SaveOutput', 'off');
    set_param(cmwOption.modelHandle, 'SaveState', 'off');
    set_param(cmwOption.modelHandle, 'SaveFinalState', 'off');

    % 開始時間
    cmwOption.startTime = 0;
    set_param('tarmodel', 'StartTime', num2str(cmwOption.startTime, 17));

    % ステップ時間
    cmwOption.stepTimeStr = get_param('tarmodel', 'FixedStep');
    try
        cmwOption.hws = get_param('tarmodel', 'modelworkspace');
        cmwOption.stepTimeNum = MBTOP.OP1.evalinModel(cmwOption.stepTimeStr, 'tarmodel', cmwOption.hws);
    catch
        set_param('tarmodel', 'FixedStep', '0.2');
        cmwOption.stepTimeNum = 0.2;
    end
    if isnan(cmwOption.stepTimeNum) || isinf(cmwOption.stepTimeNum)
        set_param('tarmodel', 'FixedStep', '0.2');
        cmwOption.stepTimeNum = 0.2;
    end

    %終了時間
    cmwOption.endTime = cmwOption.stepTimeNum * 2;
    set_param('tarmodel', 'StopTime', num2str(cmwOption.endTime, 17));

    % データ入力設定
    cmwOption.externalInput = 'cmwOption.data{1}, ';
    if ~isempty(cmwOption.externalInput)
        set_param('tarmodel', 'LoadExternalInput', 'on');
        set_param('tarmodel', 'ExternalInput', cmwOption.externalInput);
    end

    % 固定値設定
    

    % Inport置き換えBlock
    cmwOption.replaceInportBlocks = { ...
    };
catch ME
    try
        close_system('tarmodel', false);
    catch
    end
    cd(cmwOption.curDir);
    rethrow(ME);
end
cd(cmwOption.curDir);

% 時間
cmwOption.time = cmwOption.stepTimeNum * [0 : 2]';

% 入力データ
cmwOption.data{1} = timeseries(double(MBTOP.OP5.castStrToNum([{'1';'2';'3';}], 'double')), cmwOption.time);
