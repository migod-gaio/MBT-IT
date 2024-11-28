% テストCLI
function testCLI( resultFolderPath, testSetting)
    %% テスト条件設定：必須項目(全テスト項目で必要なフィールド設定)
    % テストモード
    testSetting.BaseInfo.testMode = 'SILS';
    % ソースファイル名
    testSetting.BaseInfo.srcFileName = {'src.c'};
    % テスト対象モデル名
    testSetting.BaseInfo.userModelFileName = 'tarmodel.slx';
    % テスト対象サブシステム名
    testSetting.BaseInfo.targetSubsystem = 'tarmodel/Subsystem';
    % テスト対象関数名
    testSetting.BaseInfo.functionName = 'Subsystem';
    % テストデータCSVファイル名
    testSetting.BaseInfo.testCsvName = {'atgData.csv'};
    %testSetting.BaseInfo.testCsvName = {''};
    % テストデータCSVファイルのATG種別
    % winAMSため省略しても問題なし
    testSetting.BaseInfo.atgKind = 'winAMS';
    
    %% テスト条件設定：任意項目(テスト条件で設定しないフィールドは作成不要)
    % PILS設定内容
    % SILSモードのため未設定
    %testSetting.PILS.buildDirName = 'sample';
    %testSetting.PILS.objFileName = 'sample';
    
    % MBTOP01オプション引数
    % 事前実行Mファイル名
    %testSetting.OP01.PreLoadMfile = 'preload.m';
    %testSetting.OP01.SearchBlockFile = 'searchblock.m';
    
    % MBTOP02オプション引数
    % マッピング種別
    testSetting.OP02.mapKind = 'PartialMatch';
    %testSetting.OP02.tlddMapping = true;
    testSetting.OP02.DDfile = fullfile(pwd, 'userDir\VM15b.dd');
    
    % MBTOP03/04オプション引数
    % マッピング種別
    %testSetting.OP34.mapKind = 'ForwardMatch';
    
    testSetting.OP07.evidenceKind = 'xml';

    %% テスト実行
    controlMBTOP.runTest( resultFolderPath, pwd, testSetting ); % 第二引数はテスト実行場所フォルダパス
end