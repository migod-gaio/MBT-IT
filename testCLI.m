% �e�X�gCLI
function testCLI( resultFolderPath, testSetting)
    %% �e�X�g�����ݒ�F�K�{����(�S�e�X�g���ڂŕK�v�ȃt�B�[���h�ݒ�)
    % �e�X�g���[�h
    testSetting.BaseInfo.testMode = 'SILS';
    % �\�[�X�t�@�C����
    testSetting.BaseInfo.srcFileName = {'src.c'};
    % �e�X�g�Ώۃ��f����
    testSetting.BaseInfo.userModelFileName = 'tarmodel.slx';
    % �e�X�g�ΏۃT�u�V�X�e����
    testSetting.BaseInfo.targetSubsystem = 'tarmodel/Subsystem';
    % �e�X�g�Ώۊ֐���
    testSetting.BaseInfo.functionName = 'Subsystem';
    % �e�X�g�f�[�^CSV�t�@�C����
    testSetting.BaseInfo.testCsvName = {'atgData.csv'};
    %testSetting.BaseInfo.testCsvName = {''};
    % �e�X�g�f�[�^CSV�t�@�C����ATG���
    % winAMS���ߏȗ����Ă����Ȃ�
    testSetting.BaseInfo.atgKind = 'winAMS';
    
    %% �e�X�g�����ݒ�F�C�Ӎ���(�e�X�g�����Őݒ肵�Ȃ��t�B�[���h�͍쐬�s�v)
    % PILS�ݒ���e
    % SILS���[�h�̂��ߖ��ݒ�
    %testSetting.PILS.buildDirName = 'sample';
    %testSetting.PILS.objFileName = 'sample';
    
    % MBTOP01�I�v�V��������
    % ���O���sM�t�@�C����
    %testSetting.OP01.PreLoadMfile = 'preload.m';
    %testSetting.OP01.SearchBlockFile = 'searchblock.m';
    
    % MBTOP02�I�v�V��������
    % �}�b�s���O���
    testSetting.OP02.mapKind = 'PartialMatch';
    %testSetting.OP02.tlddMapping = true;
    testSetting.OP02.DDfile = fullfile(pwd, 'userDir\VM15b.dd');
    
    % MBTOP03/04�I�v�V��������
    % �}�b�s���O���
    %testSetting.OP34.mapKind = 'ForwardMatch';
    
    testSetting.OP07.evidenceKind = 'xml';

    %% �e�X�g���s
    controlMBTOP.runTest( resultFolderPath, pwd, testSetting ); % �������̓e�X�g���s�ꏊ�t�H���_�p�X
end