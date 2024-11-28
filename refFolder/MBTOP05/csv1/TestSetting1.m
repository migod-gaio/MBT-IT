
cmwOption.curDir = pwd;
try

    cd('Z:\ModelVariation\Normal\resFolder\MBTOP05\csv1');
    load_system('Z:\ModelVariation\Normal\resFolder\MBTOP05\csv1\tarmodel');
    

    if isempty(strfind(get_param('tarmodel', 'Description'), '###CmwHarnessModel###'))
        throw(MException('CMWOption:error', 'Non-harness models have been specified for validation.'));
    end

    cmwOption.modelHandle = get_param('tarmodel', 'Handle');
    
    % �R���t�B�O���[�V�����p�����[�^�ݒ�
    set_param(cmwOption.modelHandle, 'SignalLogging', 'on');                        % �M�����O�ݒ�(on/off)
    set_param(cmwOption.modelHandle, 'SignalLoggingName', 'logsout');               % �M�����O�ݒ�(���O��)
    set_param(cmwOption.modelHandle, 'SignalLoggingSaveFormat', 'Dataset');         % �M�����O�ݒ�(�t�H�[�}�b�g)
    set_param(cmwOption.modelHandle, 'SaveTime', 'on');                             % ���ԕۑ��ݒ�
    set_param(cmwOption.modelHandle, 'TimeSaveName', 'tout');                       % ���Ԃ̕ۑ��ϐ���
    set_param(cmwOption.modelHandle, 'SaveFormat', 'Array');                        % ���ԕۑ��̌`��(�z��)
    set_param(cmwOption.modelHandle, 'LimitDataPoints', 'on');                      % ���Ԃ̃f�[�^�_���̃��~�b�g����
    set_param(cmwOption.modelHandle, 'MaxDataPoints', '1');                         % ���Ԃ̃f�[�^�_���̃��~�b�g�����l
    set_param(cmwOption.modelHandle, 'StrictBusMsg', 'ErrorOnBusTreatedAsVector');
    set_param(cmwOption.modelHandle, 'ReturnWorkspaceOutputs', 'off');              % �P��̃I�u�W�F�N�g�Ƃ��ăV�~�����[�V�����o�͂�ۑ����Ȃ�
    set_param(cmwOption.modelHandle, 'SaveOutput', 'off');
    set_param(cmwOption.modelHandle, 'SaveState', 'off');
    set_param(cmwOption.modelHandle, 'SaveFinalState', 'off');

    % �J�n����
    cmwOption.startTime = 0;
    set_param('tarmodel', 'StartTime', num2str(cmwOption.startTime, 17));

    % �X�e�b�v����
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

    %�I������
    cmwOption.endTime = cmwOption.stepTimeNum * 2;
    set_param('tarmodel', 'StopTime', num2str(cmwOption.endTime, 17));

    % �f�[�^���͐ݒ�
    cmwOption.externalInput = 'cmwOption.data{1}, ';
    if ~isempty(cmwOption.externalInput)
        set_param('tarmodel', 'LoadExternalInput', 'on');
        set_param('tarmodel', 'ExternalInput', cmwOption.externalInput);
    end

    % �Œ�l�ݒ�
    

    % Inport�u������Block
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

% ����
cmwOption.time = cmwOption.stepTimeNum * [0 : 2]';

% ���̓f�[�^
cmwOption.data{1} = timeseries(double(MBTOP.OP5.castStrToNum([{'1';'2';'3';}], 'double')), cmwOption.time);
